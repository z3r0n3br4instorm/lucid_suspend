#include "notification_bridge.h"
// #include <dbus/dbus.h>

// int send_notification(const char *summary, const char *body) {
//     DBusConnection *connection;
//     DBusMessage *message;
//     DBusError error;

//     // Initialize the error
//     dbus_error_init(&error);

//     // Connect to the session bus
//     connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
//     if (dbus_error_is_set(&error)) {
//         fprintf(stderr, "Connection Error (%s)\n", error.message);
//         dbus_error_free(&error);
//         return -1;
//     }

//     // Create a new notification message
//     message = dbus_message_new_method_call(
//         "org.freedesktop.Notifications",
//         "/org/freedesktop/Notifications",
//         "org.freedesktop.Notifications",
//         "Notify"
//     );

//     if (message == NULL) {
//         fprintf(stderr, "Message Null\n");
//         return -1;
//     }

//     // Append arguments to the message
//     const char *app_name = "ZRN Power";
//     const char *icon_name = "dialog-information";
//     int replaces_id = 0;
//     const char *app_icon = NULL;
//     const char *category = NULL;
//     const char *hint = NULL;

//     dbus_message_append_args(
//         message,
//         DBUS_TYPE_STRING, &app_name,
//         DBUS_TYPE_STRING, &icon_name,
//         DBUS_TYPE_INT32, &replaces_id,
//         DBUS_TYPE_STRING, &summary,
//         DBUS_TYPE_STRING, &body,
//         DBUS_TYPE_ARRAY, DBUS_TYPE_STRING_AS_STRING, &category,
//         DBUS_TYPE_ARRAY, DBUS_TYPE_STRING_AS_STRING, &hint,
//         DBUS_TYPE_INVALID
//     );

//     // Send the message
//     if (!dbus_connection_send(connection, message, NULL)) {
//         fprintf(stderr, "Out Of Memory!\n");
//         return -1;
//     }

//     // Free the message
//     dbus_message_unref(message);

//     // Flush the connection
//     dbus_connection_flush(connection);

//     return 0;
// }

// Send Notifications system method
//
int send_notification(const char *summary, const char *body) {
    char command[256];
    snprintf(command, sizeof(command), "dbus-send --session --type=method_call --dest=org.freedesktop.Notifications /org/freedesktop/Notifications org.freedesktop.Notifications.Notify string:\"ztOS C.O.R.E\" uint32:0 string:\"dialog-information\" string:\"%s\" string:\"%s\" array:string: int32:5000", summary, body);
    return system(command);
}
