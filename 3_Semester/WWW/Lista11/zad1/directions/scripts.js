document.addEventListener('DOMContentLoaded', onLoad);

function onLoad() {            
    let showBtn = document.getElementById('newRoute');

    showBtn.addEventListener('click', updateRoute);
}

var map;
var directionsManager, destWaypoint;

function GetMap() {
    map = new Microsoft.Maps.Map('#myMap', {
        center: new Microsoft.Maps.Location(52.7122991, 17.6077062),
        zoom: 8
    });
    
    //Load the directions module.
    Microsoft.Maps.loadModule('Microsoft.Maps.Directions', function () {
        //Create an instance of the directions manager.
        directionsManager = new Microsoft.Maps.Directions.DirectionsManager(map);

        //Create waypoints to route between.
        var startingWaypoint = new Microsoft.Maps.Directions.Waypoint({ address: 'Rzym', location: new Microsoft.Maps.Location(52.7122991, 17.5946062) });
        directionsManager.addWaypoint(startingWaypoint);

        //Specify the element in which the itinerary will be rendered.
        directionsManager.setRenderOptions({ itineraryContainer: '#directionsItinerary' });

        //Calculate directions.
        directionsManager.calculateDirections();
    });
}

function updateRoute() {
    let destValue = document.getElementById('destination').value;
    
    if(destValue == '')
        return;

    directionsManager.removeWaypoint(destWaypoint);
    
    // adds marker to destination value
    destWaypoint = new Microsoft.Maps.Directions.Waypoint({ address: destValue });
    directionsManager.addWaypoint(destWaypoint);
    
    // Calculate directions and render updated map
    directionsManager.calculateDirections();
}