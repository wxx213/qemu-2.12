#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu-common.h"
#include "trace.h"
#include "exec/address-spaces.h"
#include "qemu/error-report.h"
#include "qemu/atomic.h"
#include "sysemu/dma.h"

#define TYPE_USR_CUST_DEVICE "usr_cust"
#define TYPE_USR_CUST_SUB_DEVICE "usr_cust_sub"

typedef struct UsrCustDevice
{
    DeviceState parent_obj;
} UsrCustDevice;

typedef struct UsrCustDeviceClass {
    /*< private >*/
    DeviceClass parent;
    /*< public >*/
    void (*realize)(UsrCustDevice *uwdev, Error **errp);
} UsrCustDeviceClass;

typedef struct UsrCustSubDevice
{
    UsrCustDevice parent_obj;
} UsrCustSubDevice;

typedef struct UsrCustSubDeviceClass {
    /*< private >*/
    UsrCustDeviceClass parent;
    /*< public >*/
    void (*realize)(UsrCustSubDevice *uwsdev, Error **errp);

} UsrCustSubDeviceClass;

#define USRCUST_DEVICE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(UsrCustDeviceClass, obj, TYPE_USR_CUST_DEVICE)
#define USRCUST_DEVICE_CLASS(klass) \
        OBJECT_CLASS_CHECK(UsrCustDeviceClass, klass, TYPE_USR_CUST_DEVICE)
#define USRCUST_DEVICE(obj) \
        OBJECT_CHECK(UsrCustDevice, (obj), TYPE_USR_CUST_DEVICE)

#define USRCUST_SUB_DEVICE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(UsrCustSubDeviceClass, obj, TYPE_USR_CUST_SUB_DEVICE)
#define USRCUST_SUB_DEVICE_CLASS(klass) \
        OBJECT_CLASS_CHECK(UsrCustSubDeviceClass, klass, TYPE_USR_CUST_SUB_DEVICE)
#define USRCUST_SUB_DEVICE(obj) \
        OBJECT_CHECK(UsrCustSubDevice, (obj), TYPE_USR_CUST_SUB_DEVICE)

static void usr_cust_device_realize(DeviceState *dev, Error **errp)
{
    UsrCustDevice *ucdev = USRCUST_DEVICE(dev);
    UsrCustDeviceClass *ucdc = USRCUST_DEVICE_GET_CLASS(dev);

    printf("usr_cust_device_realize enter\n");

    if(ucdc->realize) {
        ucdc->realize(ucdev, errp);
    }
}

static void usr_cust_device_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    printf("usr_cust_device_class_init enter\n");

    dc->realize = usr_cust_device_realize;
}

static void usr_cust_instance_init(Object *obj)
{
    printf("usr_cust_instance_init enter\n");
}

// sub device
static void usr_cust_sub_device_realize(UsrCustDevice *ucdev, Error **errp)
{
    printf("usr_cust_sub_device_realize enter\n");
}

static void usr_cust_sub_device_class_init(ObjectClass *klass, void *data)
{
    UsrCustDeviceClass *ucdc = USRCUST_DEVICE_CLASS(klass);

    printf("usr_cust_sub_device_class_init enter\n");

    ucdc->realize = usr_cust_sub_device_realize;
}

static void usr_cust_sub_instance_init(Object *obj)
{
    printf("usr_cust_sub_instance_init enter\n");
}

static const TypeInfo usr_cust_device_info = {
    .name = TYPE_USR_CUST_DEVICE,
    .parent = TYPE_DEVICE,
    .instance_init = usr_cust_instance_init,
    .instance_size = sizeof(UsrCustDevice),
    .class_init = usr_cust_device_class_init,
    .class_size    = sizeof(UsrCustDeviceClass),
};

static const TypeInfo usr_cust_sub_device_info = {
    .name = TYPE_USR_CUST_SUB_DEVICE,
    .parent = TYPE_USR_CUST_DEVICE,
    .instance_init = usr_cust_sub_instance_init,
    .instance_size = sizeof(UsrCustSubDevice),
    .class_init = usr_cust_sub_device_class_init,
    .class_size    = sizeof(UsrCustSubDeviceClass),
};

static void usr_cust_register_types(void)
{
    type_register_static(&usr_cust_device_info);
    type_register_static(&usr_cust_sub_device_info);
}

type_init(usr_cust_register_types)
