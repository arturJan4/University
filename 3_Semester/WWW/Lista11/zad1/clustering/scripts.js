const proxyurl = `https://cors-anywhere.herokuapp.com/`;

function GetMap() {
    var map = new Microsoft.Maps.Map('#myMap', {
        credentials: '[Your key here]',
        zoom: 6
    });

    infobox = new Microsoft.Maps.Infobox(map.getCenter(), {
        visible: false
    });
    //Assign the infobox to a map instance.
    infobox.setMap(map);

    var pins = [];
    $.getJSON("data.json", function(data){
        let len = data.length;
        for (let i = 0; i < len; i++) {
            let latitude = parseFloat(data[i].gegrLat.replace(',','.'));
            let longitude = parseFloat(data[i].gegrLon.replace(',','.'));
            let loc = new Microsoft.Maps.Location(latitude, longitude);
        
            let pin = new Microsoft.Maps.Pushpin(loc, {'draggable': false });
            
            pin.metadata = {
                title: data[i].id,
                description: data[i].stationName
            };
            Microsoft.Maps.Events.addHandler(pin, 'click', pushpinClicked);
            pins.push(pin);
        }
    }).fail(function(){
        console.log("An error has occurred.");
    });

    Microsoft.Maps.loadModule("Microsoft.Maps.Clustering", function () {
        //Create a ClusterLayer and add it to the map.
        clusterLayer = new Microsoft.Maps.ClusterLayer(pins);

        //Add a click event to the clusterLayer
        //Microsoft.Maps.Events.addHandler(clusterLayer, 'click', clusterClicked);

        map.layers.insert(clusterLayer);
    });
}

function pushpinClicked(e) {    // Straight from BING docs
    //Make sure the infobox has metadata to display.
    if (e.target.metadata) {
        //Set the infobox options with the metadata of the pushpin.
        infobox.setOptions({
            location: e.target.getLocation(),
            title: e.target.metadata.title,
            description: e.target.metadata.description,
            visible: true
        });
    }
    
    $.getJSON(proxyurl + 'http://api.gios.gov.pl/pjp-api/rest/aqindex/getIndex/' + e.target.metadata.title, function(data) {
        $("#airData").empty();
        $("#airData").append(JSON.stringify(data, null, 4));
    });
}
