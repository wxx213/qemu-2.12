#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "trace.h"
#include "exec/address-spaces.h"
#include "qemu/error-report.h"
#include "qemu/atomic.h"
#include "sysemu/dma.h"

#define TYPE_USR_WXX_DEVICE "usr_wxx"
#define TYPE_USR_WXX_SUB_DEVICE "usr_wxx_sub"

static void usr_wxx_device_realize(DeviceState *dev, Error **errp)
{
    printf("usr_wxx_device_realize enter\n");
}

static void usr_wxx_device_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    printf("usr_wxx_device_class_init enter\n");

    dc->realize = usr_wxx_device_realize;
}

static void usr_wxx_instance_init(Object *obj)
{
    printf("usr_wxx_instance_init enter\n");
}

// sub device
static void usr_wxx_sub_device_realize(DeviceState *dev, Error **errp)
{
    printf("usr_wxx_sub_device_realize enter\n");
}

static void usr_wxx_sub_device_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    printf("usr_wxx_sub_device_class_init enter\n");

    dc->realize = usr_wxx_sub_device_realize;
}

static void usr_wxx_sub_instance_init(Object *obj)
{
    printf("usr_wxx_sub_instance_init enter\n");
}

static const TypeInfo usr_wxx_device_info = {
    .name = TYPE_USR_WXX_DEVICE,
    .parent = TYPE_DEVICE,
    .instance_init = usr_wxx_instance_init,
    .class_init = usr_wxx_device_class_init,
};

static const TypeInfo usr_wxx_sub_device_info = {
    .name = TYPE_USR_WXX_SUB_DEVICE,
    .parent = TYPE_USR_WXX_DEVICE,
    .instance_init = usr_wxx_sub_instance_init,
    .class_init = usr_wxx_sub_device_class_init,
};

static void usr_wxx_register_types(void)
{
    type_register_static(&usr_wxx_device_info);
    type_register_static(&usr_wxx_sub_device_info);
}

type_init(usr_wxx_register_types)
