
function calc_tipo1 (op1, $, dri) {
  //var $ = this[$1];
  //var str = JSON.stringify($1);
  //return $1.tax_registration_number;
  var op = parseInt(op1);
  //var $ = this[$1];
  //var $ = dados1;
  var $dri = parseInt(dri);
  //return (((((($.tax_registration_number+(": A idade de "))+($.lines[$._dri].gajo ? ("tipo") : ("tipa")))+(" "))+$.lines[$._dri].field2)+(" é "))+($.lines[$._dri].field1));

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
