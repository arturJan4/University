document.addEventListener('DOMContentLoaded', onLoad);

function onLoad() {            
    let showBtn = document.getElementById('showBtn'),
    deleteBtn = document.getElementById('deleteBtn');

    showBtn.addEventListener('click', showCurrentPushpin);
    deleteBtn.addEventListener('click', deleteCurrentPushpin);
}

var map;
function GetMap()
{
    map = new Microsoft.Maps.Map('#myMap', {
        center: new Microsoft.Maps.Location(51.1108914,17.0530772),
        mapTypeId: Microsoft.Maps.MapTypeId.aerial, //road
        zoom: 16,
    });

    //Create an infobox at the center of the map but don't show it.
    infobox = new Microsoft.Maps.Infobox(map.getCenter(), {
        visible: false
    });
    //Assign the infobox to a map instance.
    infobox.setMap(map);
    
    Microsoft.Maps.Events.addHandler(map, 'dblclick', processDblClick);
}

// proccess map double click event (creating a new pushpin at mouse location)
function processDblClick(e) {
    // zooming when double-clicking hack
    map.setOptions({ disableZooming: true });
    setTimeout(function () { return map.setOptions({ disableZooming: false }); });

    // create a new pushpin at mouse location
    var location = e.location
    var pushpin = new Microsoft.Maps.Pushpin(location, {'draggable': false });
    map.entities.push(pushpin);
    
    // add pushpin to dropdown list
    var opt = document.createElement('option');
    opt.value = pushpin.id;
    // coords (szerokosc, dlugosc)
    opt.innerHTML = pushpin.entity.id + ": " + location.latitude + ', ' + location.longitude;
    dropdown.appendChild(opt);
    
    showInfobox(infobox, location); 
}
// show pushpin at given location
function showInfobox(infobox, location) {
    infobox.setOptions({
        location: location,
        title: "TO TUTAJ",
        description: "",
        visible: true
        });
}

function showCurrentPushpin() {
    let dropdown =  document.getElementById('dropdown');
    let pushpinId = dropdown.value;
    
    let pushpin = getPushpinById(pushpinId);
    showInfobox(infobox, pushpin.getLocation());
} 

function deleteCurrentPushpin() {
    let dropdown =  document.getElementById('dropdown');
    let pushpinId = dropdown.value;

    let pushpin = getPushpinById(pushpinId);
    map.entities.remove(pushpin);
    
    infobox.setOptions({
        visible: false
    });
    
    let len = dropdown.length;
    for (let i=0; i < len; i++) {
        if (dropdown.options[i].value == pushpinId) {
            dropdown.remove(i);
            i -= 1; // updating because of deletion !
            len -= 1;
        }
    }
}

function getPushpinById(id) {
    var pin;
    let len = map.entities.getLength();

    for(let i=0; i < len; i++){
        pin = map.entities.get(i);

         if(pin && pin.id === id) {
            return pin;
        }
    }
}
