var $ = {
  _dri: 0,
  v1: 20.0,
  tax_registration_number: '178985112',
  lines: [
    {
      field1: 53,
      field2: 'eurico',
      gajo: true
    },
    {
      field1: 20,
      field2: 'bruno',
      gajo: true
    }
  ]
}

print(((((($.tax_registration_number+(": A idade de "))+($.lines[$._dri].gajo ? ("tipo") : ("tipa")))+(" "))+$.lines[$._dri].field2)+(" é "))+($.lines[$._dri].field1+ 0.5));
//console.time('expr')
/*
let x;
let cnt = 30000;

var t0 = new Date().getTime();
//var t0 = performance.now();
for (var i = 0; i < cnt; i++){
  x = (((((($.tax_registration_number+(": A idade de "))+($.lines[$._dri].gajo ? ("tipo") : ("tipa")))+(" "))+$.lines[$._dri].field2)+(" é "))+($.lines[$._dri].field1+i));
}
var t1 = new Date().getTime();
//var t1 = performance.now();
//console.timeEnd('expr');

print("elapsed time: " + (t1 - t0)+ "ms");
print("nr of operations: "+cnt+" x="+x);



/*
print((((9+((4*3)/(9-21)))>5)&&((6/11)<=12)));
print(parseInt(Math.abs((-((5+23.23))*5))));
print((((5*4)/23)==((6+2)-4)));
print(("teste").length===0);
print(("teste").substring(2,4));
print(("teste").replace((("e")+("s")),("ab")));
print((("teste").length===0 ? ("ola") : (("ola2: ")+("teste2"))));
print(((6==1) ? ("Original") : ((1).toString()+("ª Via"))));
print(("teste").indexOf((("es")+("t"))));
print((((((($.tax_registration_number+(": A idade de "))+($.lines[$._dri].gajo ?
      ("tipo") : ("tipa")))+(" "))+$.lines[$._dri].field2)+(" é "))+($.lines[$._dri].field1+0.5)));
*/
