const capitalize = (s) => {
  if (typeof s !== 'string') return '';
  return s.charAt(0).toUpperCase() + s.slice(1);
};

document.addEventListener('DOMContentLoaded', onLoad);
var _carsSelect;
var _modelSelect;
var _radioSelectModel;
var _radioSelectMarka;
var _nowa;
var _dodaj;

function onLoad() {
  _carsSelect = document.getElementById('cars');
  _modelSelect = document.getElementById('carsModel');
  _radioSelectModel = document.getElementById('modelRadio');
  _radioSelectMarka = document.getElementById('markaRadio');
  _nowa = document.getElementById('newPosition');
  _dodaj = document.getElementById('dodaj');

  _carsSelect.addEventListener('change', updateAll);
  _dodaj.addEventListener('click', addNew);
  
  updateCars(_carsSelect, CarsModelData.carsModel);
  updateAll();
}

var CarsModelData = {
  'carsModel': {
      ford: {
          text: ['Fiesta', 'Flex'],
          value: ['fiesta', 'flex']
      },
      fiat: {
          text: ['Panda', 'Fiorino'],
          value: ['panda', 'fiorino']
      }
  }    
};

function updateAll()
{
  var current = _carsSelect.value;
  if(!current) {
    current = Object.keys(CarsModelData.carsModel)[0];
  }

  console.log(current);
  updateSelections(_modelSelect, CarsModelData.carsModel[current]);
}

function updateCars(target,data) {
  target.innerHTML = "";
  var file = document.createDocumentFragment();
  var options;
  
  function addSelect(data) {
    var file = document.createDocumentFragment();
    var appended;
    
    for(var key in data){
      if (data.hasOwnProperty(key)){
        appended = document.createElement("option");
        appended.appendChild(document.createTextNode(capitalize(key)));
        appended.value = key;
        file.appendChild(appended);
      }
    }
    return file;
  }

  options = addSelect(data);
  file.appendChild(options);
  target.appendChild(file);
}

function updateSelections(target,data) {
  target.innerHTML = "";
  var file = document.createDocumentFragment();
  var options;

  function addSelect(data) {
    var file = document.createDocumentFragment();
    var appended;
    var length = data.text.length;

    for(var i = 0; i < length; i++) {
      appended = document.createElement("option");
      appended.appendChild(document.createTextNode(data.text[i]));
      
      if(data.value) {
        appended.value = data.value[i];
      }
      
      file.appendChild(appended);
    }
    return file;
  }

  options = addSelect(data);
  file.appendChild(options);
  target.appendChild(file);
}

function addNew() {
  if(!_nowa.value) {
    alert("Nowa pozycja nie może być pusta");
    return;
  }
  if(_radioSelectMarka.checked) {
    CarsModelData.carsModel[_nowa.value] = {text:[],value:[]};
    
    updateCars(_carsSelect,CarsModelData.carsModel);
    updateSelections(_modelSelect, CarsModelData.carsModel[_nowa.value]);
    _carsSelect.value = _nowa.value;
  }
  else if(_radioSelectModel.checked) {
    var current = _carsSelect.value;
    if(!current) {
      current = Object.keys(CarsModelData.carsModel)[0];
    }
    console.log(current);
    CarsModelData.carsModel[current]["text"].push(capitalize(_nowa.value));
    CarsModelData.carsModel[current]["value"].push(_nowa.value);
    
    updateSelections(_modelSelect, CarsModelData.carsModel[current]);
    _modelSelect.value = _nowa.value;
  }
  else {
    alert("error - radiobox");
    return;
  }

  _nowa.value = "";
}