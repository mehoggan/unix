#include <dlfcn.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void init_dynamic_api(void);

typedef int (*dynamic_api_func_init) (uint32_t a);
static int init_DEFAULT (uint32_t a);
extern int init_REAL (uint32_t a);

typedef struct {
  dynamic_api_func_init init;
} dynamic_api_jump_table;

static int init_DEFAULT(uint32_t a);

static dynamic_api_jump_table jump_table = {
  init_DEFAULT,
};

static int init_DEFAULT (uint32_t a)
{
  init_dynamic_api();
  return jump_table.init(a);
}

int init (uint32_t a)
{
  return jump_table.init (a);
}

typedef int32_t (*dynamic_api_entryfunc)(uint32_t apiver, void *table,
  uint32_t tablesize);

extern __attribute__ ((visibility("default")))
  int32_t dynamic_api_entry(uint32_t, void *, uint32_t);

int32_t
dynamic_api_entry(uint32_t apiver, void *table, uint32_t tablesize)
{
  dynamic_api_jump_table *output_jump_table = (dynamic_api_jump_table *)table;

  if (apiver != 1) {
    return -1;
  } else if (tablesize > sizeof (jump_table)) {
    return -1;
  }

  jump_table.init = init_REAL;

  if (output_jump_table != &jump_table) {
    memcpy(output_jump_table, &jump_table, tablesize);
  }

  return 0;
}

static void
init_dynamic_api(void)
{
//if (!NOT_ALREAD_INIT) {
    void *lib;
    void *sym;

    const char *libname = getenv("DYNAMIC_API");
    dynamic_api_entryfunc entry = dynamic_api_entry;

    sym = NULL;

    if (libname) {
      lib = dlopen("dynamic_api_entry", 0x00002);
      if (lib != NULL) {
        sym = dlsym(lib, "dynamic_api_entry");
        if (sym == NULL) {
          dlclose(lib);
        }
      }

      if (!sym) {
        entry = dynamic_api_entry;
      } else {
        entry = (dynamic_api_entryfunc)sym;
      }
    }

    if (entry(1, &jump_table, sizeof (jump_table)) < 0) {
      if (entry != dynamic_api_entry) {
        if (!dynamic_api_entry(1, &jump_table, sizeof (jump_table))) {
        }
      }
    }
//}
}
