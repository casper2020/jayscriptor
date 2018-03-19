
function calc_tipo1 (op1, $1, dri) {

  var op = parseInt(op1);
  var $ = this[$1];
  var $dri = parseInt(dri);

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

let cnt0=1;
let cnt1=1000;
let cnt2=4;
var n = 0;
var array = [];

//var t0 = performance.now();
for(var ii=0; ii<cnt0; ii++){
  for(var i=0; i<cnt1; i++){
    for(var l=1; l<=cnt2; l++){
      array[n] = calc_tipo1(l,"$",i);
      n++;
    }
  }
}
//var t1 = performance.now();
//print("elapsed time: " + (t1 - t0) + "ms");
print("nr of operations: " + n);
