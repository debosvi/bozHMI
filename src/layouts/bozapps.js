var filesadded = ""		// list of files already added
var current_div = ""		// current div id
var all_divs = []		// list aof div id's

function checkloadjscssfile(filename, filetype) {
    if (filesadded.indexOf("[" + filename + "]") == -1) {
        loadjscssfile(filename, filetype);
        filesadded += "[" + filename + "]";	//List of files added in the form "[filename1],[filename2],etc"
    } else {
        alert("file already added!");
    }
}

function loadjscssfile(filename, filetype) {
    if (filetype == "js") {	//if filename is a external JavaScript file
        var fileref = document.createElement('script');
        fileref.setAttribute("type", "text/javascript");
        fileref.setAttribute("src", filename);
    } 
    else if (filetype == "css") {	//if filename is an external CSS file
        var fileref = document.createElement("link");
        fileref.setAttribute("rel", "stylesheet");
        fileref.setAttribute("type", "text/css");
        fileref.setAttribute("href", filename);
    }

    if (typeof fileref != "undefined") {
        document.getElementsByTagName("head")[0].appendChild(fileref);
    }
}

function load_bundle(url) {
    $.getJSON(url, function(data) {
        $( "<img>" ).attr( "src", data.icons.app ).appendTo( "#images" );
        $( "#titles" ).append("<p>Short: " + data.titles.short + ", extended: " + data.titles.extended + "</p>" );
        all_divs.push(data.titles.short);

        $.get(data.pages.main, function( content ) {
            $( "#contents" ).append("<div id=\"" + data.titles.short + "\">" +  content + "</div>" );
            if ( ! current_div.length ) {
                current_div = data.titles.short;
            } else {
                $( "#" + data.titles.short ).hide();
            }
        })
        .error(function() { 
            alert("HTML error"); 
        })

        $.each(data.headers.css, function(i) {
            loadjscssfile(data.headers.css[i], "css");
        })

        $.each(data.headers.js, function(i) {
            loadjscssfile(data.headers.js[i], "js");
        })

    })
    .error(function() { 
        alert("JSON error");
    })
}

function next_app() {
    curidx=all_divs.lastIndexOf(current_div);
    curid=all_divs[curidx];
    console.log("curidx: " + curidx)
    console.log("curid: " + curid)

    newidx=(all_divs.lastIndexOf(current_div)+1) % all_divs.length;
    newid=all_divs[newidx];
    console.log("newidx: " + newidx)
    console.log("newid: " + newid)

    current_div=newid;
    $("#" + curid ).hide("fast", function() { 
        $("#" + newid ).show("fast"); 
    })
}

