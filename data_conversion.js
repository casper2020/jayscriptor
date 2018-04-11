<script>

function convert_json($){

	// dynamically create variables
	var type_id_map = {};
	for (var r in $.data.relationships ) {

    	var src_var = eval("$.data.relationships."+r);
    	var new_var = eval("$."+r+"=new Array(" + src_var.length + ")");
    	new_var = src_var.data;

	    var idx = 0;
    	for ( var o of new_var ) {
        	var key = o.type + '$' + o.id;
        	var array = type_id_map[key];
        	if ( undefined == array ) {
            	array = []
            	type_id_map[key] = array
        	}
        	array.push({"variable": r, "order": idx, "id": o.id});
        	++idx;
    	}
	}

  // collect objects and link with dynamically created variables
	for (var entry of $.included){
		var key = entry.type + '$' + entry.id;
		var interest_array = type_id_map[key];
        for ( var e of interest_array ) {
        	$[e.variable][e.order] = entry.attributes;
	        $[e.variable][e.order].id = entry.id;
	        $[e.variable][e.order].type = entry.type;
        }
	}

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
