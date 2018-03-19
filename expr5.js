function getKeyByValue(object, value) {
  return Object.keys(object).find(key => object[key] === value);
}

function convert_json($){
  $.lines = $.data.relationships.lines.data;

  var map = {};
  var ind=0;
  for (var id of $.lines) {
    map[ind]=id.id;
    ind++;
  }

  ind=0;
  for (var id of $.included){
    var index = getKeyByValue(map, id.id);
    $.lines[index] = $.included[ind].attributes;
    ind++;
  }

  for (var id of $.included){
    var index = getKeyByValue(map, id.id);
    $.lines[index].id = id.id;
  }

  return $;
}

function calc_tipo1 (op1, $, dri) {
  var op = parseInt(op1);
  var $dri = parseInt(dri);

  return $.lines[2].account_description;

  switch (op) {
    case 1:
      return $.tax_registration_number;
    case 2:
      return (((((($.tax_registration_number+(": A idade de "))+($.lines[$dri].gajo ? ("tipo") : ("tipa")))+(" "))+$.lines[$dri].field2)+(" é "))+($.lines[$dri].field1));
    case 3:
      return ($.v1+(": Isto é ")+$.lines[$dri].field2+(" é ")+($.lines[$dri].field1));
    case 4:
      return $.tax_registration_number / 100;
    default:
      return op;
  }
}
