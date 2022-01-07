#ifndef __OBJC__
typedef void* id;
#endif

id api_getlocation();
const char* api_location_to_text(id location);
void api_free_location(id location);
id get_degree();
