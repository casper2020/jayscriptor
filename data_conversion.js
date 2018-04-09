<script>
function getKeyByValue(object, value) {
  return Object.keys(object).find(key => object[key] === value);
}
function convert_json($){


	var type_id_map = {};
  for (var r in $.data.relationships ) {

	var src_var = eval("$.data.relationships."+r);
	var new_var = eval("$."+r+"={}");
    new_var = src_var.data;

	var idx = 0;
    for ( var o of new_var ) {
	    var key = o.type + '_' + o.id;
	    var array = type_id_map[key];
        if ( undefined == array ) {
            array = []
        	type_id_map[key] = array
        }
		array.push({"variable": r, "order": idx});
		++idx;
    }

  }
	for (var entry of $.included){
		var key = entry.type + '_' + entry.id;
		var obj = type_id_map[key];
		console.log(key + " ~> " + obj.variable + " at " + obj.order);
	}

	console.log($);
	console.log(type_id_map);

  return $;
}
var obj = {
	"data": {
		"type": "documents",
		"id": 9852372,
		"attributes": {
			"name": "the name"
		},
		"relationships": {
			"lines": {
				"data": [{
					"type": "doc_lines",
					"id": 260119
				}]
			},
			"ananas": {
				"data": [{
					"type": "ananas",
					"id": 26011965
				}]
			},
			"batatas": {
				"data": [{
					"type": "batatinha",
					"id": 1
				},{
					"type": "doc_lines",
					"id": 260119
				}]
			}
		}
	},
	"included": [{
			"type": "doc_lines",
			"id": 260119,
			"attributes": {
				"item_name": "é mesmo uma linha"
			}
		}, {
			"type": "ananas",
			"id": 26011965,
			"attributes": {
				"item_name": "é mesmo um ananas"
			}
		},
		{
			"type": "batatinha",
			"id": 1,
			"attributes": {
				"item_name": "é mesmo uma batata"
			}
		}
	]
}
// console.log(obj);
console.log(convert_json(obj));

</script>
