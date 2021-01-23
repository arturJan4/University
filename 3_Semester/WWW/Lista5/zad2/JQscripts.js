const RSS_URL = `https://tvn24.pl/najnowsze.xml`;
const proxyurl = `https://cors-anywhere.herokuapp.com/`;

/*parsed = true if array of items is passed, else it must search for items
 *format
 *{
 *  title:
 *  link:
    description:
 *}
 * outputs an array of objects (dictionaries) from a xml RSS data
 */
function extractItems(xmlData, parsed)
{
    function addItem(item) {
      let title = item.find("title").text();
      let linksText = item.find("link").text();
      let description = item.find("description").text();

      let links = $("<a>").append(linksText);
      links.attr("href", linksText)
      items.push({
        "title" : title,
        "link" : links,
        "description": description
        });
    }

    items = [];
    if(parsed) {
      xmlData.each(function() {addItem($(this));});
    }
    else {
      xmlData.find("item").each(function() {addItem($(this));});
    }

    return items;
}

// populates using dictionary
function populateTable(table, items)
{
    table.empty();
    items.forEach(function (curr_item) {
      let _item = $("<li>").addClass("news-item");
      _item.append($("<div>").addClass("news-item-title").append(curr_item.title));
      _item.append($("<div>").addClass("news-item-links").append(curr_item.link));
      _item.append($("<div>").addClass("news-item-description").append(curr_item.description));
      table.append(_item);
    });
}

$(function() { 
  var xmlDoc;
  var itemsRSS = [];
  
  $.get(RSS_URL, function(data) {
    xmlDoc = $(data);
    itemsRSS = extractItems(xmlDoc,false);
    populateTable($("#news"),itemsRSS.slice(0,5));
  });
  
  // local version in case if cors everywhere malfunctions
  /*
  $.get("testRSS.xml", function(data) {
    xmlDoc = $(data);
    itemsRSS = extractItems(xmlDoc,false);
    populateTable($("#news"),itemsRSS.slice(0,5));
  });
  */

  $("#searchbtn").on("click", function() {
    let value = $("#searchphrase").val();
    let foundItems = xmlDoc.xpath(`//item[contains(description, "${value}")]`);
    // true because we have an array of items already down nested structure
    populateTable($("#news-found"),extractItems(foundItems,true));
  });
});