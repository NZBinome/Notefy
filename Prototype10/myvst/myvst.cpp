#include "../vst/aeffect.h"
#include "../vst/vstfxstore.h"
#include "myvst.h"

AEffect* loadPlugin() {
  AEffect *plugin = NULL;
  char *vstPath = "c:\\wherever\\the\\plugin\\is\\located.vst";

  modulePtr = LoadLibrary(vstPath);
  if(modulePtr == NULL) {
    printf("Failed trying to load VST from '%s', error %d\n",
      vstPath, GetLastError());
    return NULL;
  }

  vstPluginFuncPtr mainEntryPoint =
    (vstPluginFuncPtr)GetProcAddress(modulePtr, "VSTPluginMain");
  // Instantiate the plugin
  plugin = mainEntryPoint(hostCallback);
  return plugin;
}
