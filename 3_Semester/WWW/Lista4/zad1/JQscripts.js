//TODO : REFACTOR
function isSubstring(str1,str2) {
    if(str1.length < 3 || str1.length > str2.length)
        return false;
    let input = str1.toLowerCase();
    let inputLen = str1.length;
    let searched = str2.toLowerCase();
    for(var i = 0; i < str1.length - inputLen + 1; i++) {
        if(searched.includes(input.substr(i, i + inputLen)))
            return true;
    }
    
    return false;
}
//let str1 = "222";
//let str2 = "test222";
//console.log(isSubstring(str1,str2));

$(function(){
    $("#searchphrase").on("keyup", function() {
        let value = $(this).val();
        let valLength = value.length;
        $("#items li").removeClass("found").removeClass("notFound");
        if(valLength >= 3) {
        $("#items li")
            .addClass("notFound")
            .filter(function(index,elem) {
                return(isSubstring(value, elem.innerHTML));
            })
            .removeClass("notFound").addClass("found");
        }
    })
})
  