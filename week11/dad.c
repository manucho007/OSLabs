/*
   An example of how the DMA mappings might be used for a PCI device. 
   The actual form of DMA operations on the PCI bus is very dependent on 
   the device being driven.  Thus, this example does not apply
   to any real device; instead, it is part of a hypothetical driver called 
   dad (DMA Acquisition Device). A driver for this device might define a 
   transfer function like this:
*/
int dad_transfer(struct dad_dev *dev, int write, void *buffer, size_t count)
{
    dma_addr_t bus_addr;
    /* Map the buffer for DMA */
    dev->dma_dir = (write ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
    dev->dma_size = count;
    bus_addr = dma_map_single(&dev->pci_dev->dev, buffer, count, dev->dma_dir);
    dev->dma_addr = bus_addr;

    /* Set up the device */
    writeb(dev->registers.command, DAD_CMD_DISABLEDMA);
    writeb(dev->registers.command, write ? DAD_CMD_WR : DAD_CMD_RD);
    writel(dev->registers.addr, cpu_to_le32(bus_addr));
    writel(dev->registers.len, cpu_to_le32(count));

    /* Start the operation */
    writeb(dev->registers.command, DAD_CMD_ENABLEDMA);
    return 0;
}

/*
   The above function maps the buffer to be transferred and starts the
   device operation.  The other half of the job must be done in the 
   interrupt service routine, which looks something like this:

   pt_regs = intel registers
*/
void dad_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
    struct dad_dev *dev = (struct dad_dev *)dev_id;

    /* Make sure it's really our device interrupting */
    /* Unmap the DMA buffer */
    /* After this call, reads by the CPU to the buffer are guaranteed 
      to see whatever the device wrote there. */
    dma_unmap_single(dev->pci_dev->dev,
                     dev->dma_addr,
                     dev->dma_size,
                     dev->dma_dir);
    /* Only now is it safe to access the buffer, copy to user, etc. */
    /*...*/
}

/*
   The DMA channel needs to be registered.
   include <asm/dma.h>
   the following functions can be used to obtain and release ownership
   of a DMA channel:
      int request_dma(unsigned int channel, const char *name);
      void free_dma(unsigned int channel);
   The channel argument is a number between 0 and 7 or a positive
   number less than MAX_DMA_CHANNELS.  On the PC, MAX_DMA_CHANNELS is 
   defined as 8 to match the hardware. The name argument is a string 
   identifying the device.  The specified name appears in the file 
   /proc/dma 
   which can be read by user programs.

   Every device using DMA needs an IRQ line as well; otherwise, it
   couldn’t signal the completion of data transfer.  Get the channel
   after getting the interrput line, release it before the interrupt
   to avoid deadlock - see below
*/

int dad_open(struct inode *inode, struct file *filp)
{
    struct dad_device *my_device;

    /* ... */
    if ((error = request_irq(my_device.irq, dad_interrupt, SA_INTERRUPT, "dad", NULL)))
        return error; /* or implement blocking open */

    if ((error = request_dma(my_device.dma, "dad")))
    {
        free_irq(my_device.irq, NULL);
        return error; /* or implement blocking open */
    }
    /* ... */
    return 0;
}

void dad_close(struct inode *inode, struct file *filp)
{
    struct dad_device *my_device;
    /* ... */
    free_dma(my_device.dma);
    free_irq(my_device.irq, NULL);
    /* ... */
}
