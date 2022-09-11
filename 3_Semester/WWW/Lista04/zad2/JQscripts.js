// subject - podmiot - liczba mnoga
var subjectG = 
["posłowie opozycji", "posłowie totalnej opozycji", "pseudodziennikarze", "nauczyciele", "feministki", "młodzi lekarze", "pseudoelity",
 "polacy", "obcokrajowcy", "kobiety", "opozycjoniści", "prawnicy", "lewacy", "zwolennicy opozycji", "zwolennicy skrajnej opozycji",
 "alimenciarze", "obrońcy pedofilów i  alimenciarzy", "sieci Sorosa", "oficjele Unii Europejskiej", "złodzieje", "wyłudzacze VAT-u", 
 "rolnicy", "przedsiębiorcy", "francuzi", "internauci", "macki Sorosa", "przypadkowi spacerowicze"];

// verb - liczba mnoga
var verbG =
["marnotrawią","szkalują", "atakują", "bezczeszczą", "zaprzeszczają", "marnują", "nie stawiają na", "chcą zatrzymać", "radzą jak obalić", "chcą sprzedać",
 "zabiorą Ci", "zniszczą Ci", "zabiorą nam", "odbiorą nam", "zniszczą nam", "krzyżuja plany na", "przeszkadzają rozwijać", "okradają"
];
// adverb - przysłówek
var adverbG = 
["dobre", "fantastyczne", "niespotykanie dobre", "cudowne", "przewyborne",
"fenomenalne", "rewelacyjne", "genialne", "świetne", "nadzwyczajne", "zjawiskowe",
"wybitne", "pierwszorzędne", "innowacyjne"];
// object
var objectG = 
["zarobki Polaków", "wyniki finansowe polskiego rządu", "wzrosty poziomu PKB", "bezpieczeństwo Polski", 
"bezpieczeństwo energetyczne Polski", "bogactwo Polaków", "polskie technologie", "nastawienie Polaków", 
"wyposażenie służby zdrowia", "odrodzenie Polski", "wstawanie Polski z kolan", "imię Polski", "sądy", 
"polskie tradycje", "reformy","programy socjalne", "działania Polskiego rządu", "tarcze antykryzysowe"];

function getRandomFromArray(arr) {
    return arr[Math.floor(Math.random() * arr.length)].toUpperCase();
}

function generateRandomTitle() {
    return getRandomFromArray(subjectG) + " " + 
           getRandomFromArray(verbG) + " " +
           getRandomFromArray(adverbG) + " " +
           getRandomFromArray(objectG);
}
console.log(generateRandomTitle());
const maxSize = Math.max(subjectG.length, verbG.length, adverbG.length, objectG.length);
$(function(){
    // populate table
    for(let i = 0; i < maxSize; i++) {
        let row = $("<tr>");
        row.append($("<td>").html(subjectG[i]));
        row.append($("<td>").html(verbG[i]));
        row.append($("<td>").html(adverbG[i]));
        row.append($("<td>").html(objectG[i]));
        $("#bsTable").append(row);
    }

    $("#generate").click(function() {
        $("#bsBar").val(generateRandomTitle());
    });
})
