/* vala_main.c generated by valac 0.36.14, the Vala compiler
 * generated from vala_main.vala, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>


#define TYPE_HELLO_WORLD (hello_world_get_type ())
#define HELLO_WORLD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_HELLO_WORLD, HelloWorld))
#define HELLO_WORLD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_HELLO_WORLD, HelloWorldClass))
#define IS_HELLO_WORLD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_HELLO_WORLD))
#define IS_HELLO_WORLD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_HELLO_WORLD))
#define HELLO_WORLD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_HELLO_WORLD, HelloWorldClass))

typedef struct _HelloWorld HelloWorld;
typedef struct _HelloWorldClass HelloWorldClass;
typedef struct _HelloWorldPrivate HelloWorldPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _HelloWorld {
	GtkApplication parent_instance;
	HelloWorldPrivate * priv;
};

struct _HelloWorldClass {
	GtkApplicationClass parent_class;
};


static gpointer hello_world_parent_class = NULL;

GType hello_world_get_type (void) G_GNUC_CONST;
enum  {
	HELLO_WORLD_0_PROPERTY
};
HelloWorld* hello_world_new (void);
HelloWorld* hello_world_construct (GType object_type);
static void hello_world_real_activate (GApplication* base);
gint hello_world_main (gchar** args, int args_length1);


HelloWorld* hello_world_construct (GType object_type) {
	HelloWorld * self = NULL;
	self = (HelloWorld*) g_object_new (object_type, "application-id", "ch.frenchguy.PiCaster", "flags", G_APPLICATION_FLAGS_NONE, NULL);
	return self;
}


HelloWorld* hello_world_new (void) {
	return hello_world_construct (TYPE_HELLO_WORLD);
}


static void hello_world_real_activate (GApplication* base) {
	HelloWorld * self;
	GtkApplicationWindow* main_window = NULL;
	GtkApplicationWindow* _tmp0_;
	self = (HelloWorld*) base;
	_tmp0_ = (GtkApplicationWindow*) gtk_application_window_new ((GtkApplication*) self);
	g_object_ref_sink (_tmp0_);
	main_window = _tmp0_;
	g_object_set ((GtkWindow*) main_window, "default-height", 300, NULL);
	g_object_set ((GtkWindow*) main_window, "default-width", 300, NULL);
	gtk_window_set_title ((GtkWindow*) main_window, "Hello World");
	gtk_widget_show_all ((GtkWidget*) main_window);
	_g_object_unref0 (main_window);
}


gint hello_world_main (gchar** args, int args_length1) {
	gint result = 0;
	HelloWorld* app = NULL;
	HelloWorld* _tmp0_;
	gchar** _tmp1_;
	gint _tmp1__length1;
	gint _tmp2_;
	_tmp0_ = hello_world_new ();
	app = _tmp0_;
	_tmp1_ = args;
	_tmp1__length1 = args_length1;
	_tmp2_ = g_application_run ((GApplication*) app, _tmp1__length1, _tmp1_);
	result = _tmp2_;
	_g_object_unref0 (app);
	return result;
}


int main (int argc, char ** argv) {
#if !GLIB_CHECK_VERSION (2,35,0)
	g_type_init ();
#endif
	return hello_world_main (argv, argc);
}


static void hello_world_class_init (HelloWorldClass * klass) {
	hello_world_parent_class = g_type_class_peek_parent (klass);
	((GApplicationClass *) klass)->activate = (void (*) (GApplication *)) hello_world_real_activate;
}


static void hello_world_instance_init (HelloWorld * self) {
}


GType hello_world_get_type (void) {
	static volatile gsize hello_world_type_id__volatile = 0;
	if (g_once_init_enter (&hello_world_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (HelloWorldClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) hello_world_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (HelloWorld), 0, (GInstanceInitFunc) hello_world_instance_init, NULL };
		GType hello_world_type_id;
		hello_world_type_id = g_type_register_static (gtk_application_get_type (), "HelloWorld", &g_define_type_info, 0);
		g_once_init_leave (&hello_world_type_id__volatile, hello_world_type_id);
	}
	return hello_world_type_id__volatile;
}



