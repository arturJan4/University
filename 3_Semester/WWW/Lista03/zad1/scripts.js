document.addEventListener('DOMContentLoaded', onLoad);

function onLoad() {
  var txtAccountNum = document.getElementById('accountNum'),
      txtPesel = document.getElementById('pesel'),
      txtBirthdate = document.getElementById('birthdate'),
      txtMailaddr = document.getElementById('mailaddr');
  
  txtAccountNum.addEventListener('focusout', function(){validateUpdate(this,"accountNum");});
  txtPesel.addEventListener('focusout', function(){validateUpdate(this,"pesel");});
  txtBirthdate.addEventListener('focusout', function(){validateUpdate(this,"birthdate");});
  txtMailaddr.addEventListener('focusout', function(){validateUpdate(this,"mailaddr");});
  document.getElementById('mainForm').onsubmit = checkForm;
}

function checkForm() {
  var valAccountNum = document.getElementById('accountNum').value,
      valPesel = document.getElementById('pesel').value,
      valBirthdate = document.getElementById('birthdate').value,
      valMailaddr = document.getElementById('mailaddr').value;

  if(validateInput(valAccountNum, "accountNum") && 
     validateInput(valPesel, "pesel")           && 
     validateInput(valBirthdate, "birthdate")   && 
     validateInput(valMailaddr, "mailaddr")) {
    alert("mockup send");
    return true;
  } 
  else {
    alert("błedne dane");
    return false;
  }
}

function validateUpdate(inputObject, inputType) {
  if(validateInput(inputObject.value, inputType)) {
    inputObject.style.borderColor = "#32CD32";
  }
  else {
    inputObject.style.borderColor = "#ff0000";
  }
}

function validateInput(value, inputType) {
  function isLeap(year) {
    return ((year % 4 === 0) && (year % 100 !== 0)) || (year % 400 === 0);
  }
  var valid = false;
  var re;
  switch(inputType) {
    case "accountNum":
      re = /^(\d\s*){26}$/;
      valid = re.test(value);
      break;
    case "pesel":
      // suma kontrolna?
      re = /^\d{11}$/;
      valid = re.test(value);
      break;
    case "birthdate":
      re = /^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[012])-(19|20)\d\d$/;
      valid = re.test(value);
      if(valid) {
        let arr = re.exec(value);
        let day = arr[1];
        let month = arr[2];
        let year = arr[3];
        if(month == 2) {
          valid = (isLeap(year)) ? day <= 29 : day <= 28;
        }
        
        if (month == 4 || month == 6 || month == 9 || month == 11)  {
          valid = (day <= 30); 
        }
      }
      break;
    case "mailaddr":
      re = /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/;
      valid = re.test(value);
      break;
    default:
      console.log(`Error unknown ${inputType} in switch validateInput statement`);
      break;
  }
  console.log(`${value}`);
  return valid;
}