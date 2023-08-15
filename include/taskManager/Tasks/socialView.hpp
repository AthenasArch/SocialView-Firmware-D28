#ifndef SOCIALVIEW_HPP
#define YOUTUBE_HPP

#include "Database/Structures/systemStatus.h"

#define YOUTUBE_API_URL(id, key) ("https://www.googleapis.com/youtube/v3/channels?part=snippet,statistics&id=" + id + "&key=" + key)
#define INSTAGRAM_API_URL(user) ("https://www.instagram.com/api/v1/users/web_profile_info/?username=" + user)
#define INSTAGRAM_USER_AGENT "Instagram 76.0.0.15.395 Android (24/7.0; 640dpi; 1440x2560; samsung; SM-G930F; herolte; samsungexynos8890; en_US; 138226743)"
#define GITHUB_API_URL(user) ("https://api.github.com/users/" + user)


#define GOOGLE_GEOLOCATION(key) ("https://www.googleapis.com/geolocation/v1/geolocate?key=" + key)
#define GOOGLE_GEOCODE(location, key) ("https://maps.googleapis.com/maps/api/geocode/json?latlng=" + location + "&result_type=street_address&key=" + key)

void socialView_task(void *pvParameters);

#endif