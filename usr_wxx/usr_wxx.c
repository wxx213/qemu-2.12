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

typedef struct UsrWxxDevice
{
    DeviceState parent_obj;
} UsrWxxDevice;

typedef struct UsrWxxDeviceClass {
    /*< private >*/
    DeviceClass parent;
    /*< public >*/
    void (*realize)(UsrWxxDevice *uwdev, Error **errp);
} UsrWxxDeviceClass;

typedef struct UsrWxxSubDevice
{
    UsrWxxDevice parent_obj;
} UsrWxxSubDevice;

typedef struct UsrWxxSubDeviceClass {
    /*< private >*/
    UsrWxxDeviceClass parent;
    /*< public >*/
    void (*realize)(UsrWxxSubDevice *uwsdev, Error **errp);

} UsrWxxSubDeviceClass;

#define USRWXX_DEVICE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(UsrWxxDeviceClass, obj, TYPE_USR_WXX_DEVICE)
#define USRWXX_DEVICE_CLASS(klass) \
        OBJECT_CLASS_CHECK(UsrWxxDeviceClass, klass, TYPE_USR_WXX_DEVICE)
#define USRWXX_DEVICE(obj) \
        OBJECT_CHECK(UsrWxxDevice, (obj), TYPE_USR_WXX_DEVICE)

#define USRWXX_SUB_DEVICE_GET_CLASS(obj) \
        OBJECT_GET_CLASS(UsrWxxSubDeviceClass, obj, TYPE_USR_WXX_SUB_DEVICE)
#define USRWXX_SUB_DEVICE_CLASS(klass) \
        OBJECT_CLASS_CHECK(UsrWxxSubDeviceClass, klass, TYPE_USR_WXX_SUB_DEVICE)
#define USRWXX_SUB_DEVICE(obj) \
        OBJECT_CHECK(UsrWxxSubDevice, (obj), TYPE_USR_WXX_SUB_DEVICE)

static void usr_wxx_device_realize(DeviceState *dev, Error **errp)
{
    UsrWxxDevice *uwdev = USRWXX_DEVICE(dev);
    UsrWxxDeviceClass *uwdc = USRWXX_DEVICE_GET_CLASS(dev);

    printf("usr_wxx_device_realize enter\n");

    if(uwdc->realize) {
        uwdc->realize(uwdev, errp);
    }
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
static void usr_wxx_sub_device_realize(UsrWxxDevice *uwdev, Error **errp)
{
    printf("usr_wxx_sub_device_realize enter\n");
}

static void usr_wxx_sub_device_class_init(ObjectClass *klass, void *data)
{
    UsrWxxDeviceClass *uwdc = USRWXX_DEVICE_CLASS(klass);

    printf("usr_wxx_sub_device_class_init enter\n");

    uwdc->realize = usr_wxx_sub_device_realize;
}

static void usr_wxx_sub_instance_init(Object *obj)
{
    printf("usr_wxx_sub_instance_init enter\n");
}

static const TypeInfo usr_wxx_device_info = {
    .name = TYPE_USR_WXX_DEVICE,
    .parent = TYPE_DEVICE,
    .instance_init = usr_wxx_instance_init,
    .instance_size = sizeof(UsrWxxDevice),
    .class_init = usr_wxx_device_class_init,
    .class_size    = sizeof(UsrWxxDeviceClass),
};

static const TypeInfo usr_wxx_sub_device_info = {
    .name = TYPE_USR_WXX_SUB_DEVICE,
    .parent = TYPE_USR_WXX_DEVICE,
    .instance_init = usr_wxx_sub_instance_init,
    .instance_size = sizeof(UsrWxxSubDevice),
    .class_init = usr_wxx_sub_device_class_init,
    .class_size    = sizeof(UsrWxxSubDeviceClass),
};

static void usr_wxx_register_types(void)
{
    type_register_static(&usr_wxx_device_info);
    type_register_static(&usr_wxx_sub_device_info);
}

type_init(usr_wxx_register_types)
