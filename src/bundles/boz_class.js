
function bozclass_create(owner, id, f, c, w, h) {
	console.log('creates BozClass id: "' + id + '" in parent: "' + owner + '"');
	this.id = id;
	this.bg[0] = f;
	this.dims['w']=w;
	this.dims['h']=h;
	this.class = c;
	
	this.draw(owner);
}

function bozclass_draw(owner) {
	console.log('draw id: "' + this.id + '"' );
	this.hide();
	var nv = jQuery('<div/>', {
		id: this.id,
		title: 'button (' + this.id + ')',
		alt: 'button (' + this.id + ')',
		style: "display: none; background-image: url('" + this.bg[0] + "'); background-repeat: no-repeat; border: 1px dashed green",
		width: this.dims['w'], height: this.dims['h'], class: this.class
	});
		
	nv.appendTo('#' + owner );
}

function bozclass_hide() {
	$('#' + this.id).hide();
}

function bozclass_show() {
	$('#' + this.id).show();
}

function bozclass_hover() {
	console.log(this.id + 'hover');
}    
	
function bozclass_hover() {
	console.log(this.id + 'hover');
}   

function bozClass() {
	this.id = -1;
	this.dims = [ -1, -1 ];
	this.class = new Array();
	this.bg = new Array();
}

bozClass.prototype.create = bozclass_create;
bozClass.prototype.draw = bozclass_draw;
bozClass.prototype.show = bozclass_show;
bozClass.prototype.hide = bozclass_hide;


function bozclass2_setstate(s) {
	var state = typeof s !== 'undefined' ? s : 0;
	console.log(this.id + ', bozclass2_state: ' + state);
	this.state = state;
	$('#' + this.id).css("background-image: url('" + this.bg[this.state] + "')");
} 

function bozClass2() {
	// this.state = 0;	

}

bozClass2.prototype = {
    get state() {
        console.log("bozClass2 getter state");
    },

    set state(s) {
		console.log("bozClass2 setter state");
    }
};

bozClass2.prototype = new bozClass();
bozClass2.prototype.constructor = bozClass2; 		
		
		