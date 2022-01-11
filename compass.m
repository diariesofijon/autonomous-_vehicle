#import <CoreLocation/CoreLocation.h>

id api_getlocation()
{
  CLLocationManager * locationManager = [[CLLocationManager alloc] init];  
  [locationManager startUpdatingLocation];
  [locationManager setDesiredAccuracy:CLLocationAccuracyNearestTenMeters];
   //[locationManager setDelegate:self];

   CLLocation* location = [locationManager location];
   return [location retain];
}

const char* api_location_to_text(id location) 
{
   NSString* newText = [NSString stringWithFormat: @"Your Position : %f %f", [location horizontalAccuracy], [location verticalAccuracy]];

   return strdup([newText UTF8String]);
}

void api_free_location(id location)
{
    [location release];
}

id get_degree()
{
    - (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
    {
       return newHeading.magneticHeading*M_PI/180;
    }
}
