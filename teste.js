console.time('expr')
let x;
let cnt = 30;
//var t0 = performance.now();
for (var i = 0; i < cnt; i++){
  x = (((((($.tax_registration_number+(": A idade de "))+($.lines[$._dri].gajo ? ("tipo") : ("tipa")))+(" "))+$.lines[$._dri].field2)+(" é "))+($.lines[$._dri].field1+i));
}
//var t1 = performance.now();
console.timeEnd('expr');
//console.log("elapsed time: " + (t1 - t0)/1000.0 + "s");
console.log("nr of operations: "+cnt+" x="+x);
