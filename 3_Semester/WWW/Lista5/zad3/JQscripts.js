const RSS_URL = `https://tvn24.pl/najnowsze.xml`;
const proxyurl = `https://cors-anywhere.herokuapp.com/`;

$(function() {
  var template = $("#news-item-temp").html();
  Mustache.parse(template);
 
  $.getJSON("rss_data.json", function(data) {
    var html = Mustache.render(template,data.rss.channel.item.slice(0,5));
    $("#news").append(html);
  });
});