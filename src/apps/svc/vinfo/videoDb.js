var fs = require('fs');
var Class = require('./Class.js');
var sql = require('sql.js');

var videoDb = Class({ 
    initialize: function(db_file) {
        console.log("videoDb construcutor: " + db_file);
        this.db_file = db_file;
        this.db = null;
    },
    checkDb: function() {
        console.log("videoDb/checkDb: " + this.db_file );
        var dbf = this.db_file;
        fs.exists(this.db_file, function(exists) {
        if (exists) {
            console.log("DB file (" + this.db_file + ") already exists");
        }
        else {
        // mongodb
            console.log("DB file (" + this.db_file + ") doesn't exists");
            var db = new sql.Database();
            // NOTE: You can also use new sql.Database(data) where
            // data is an Uint8Array representing an SQLite database file

            // Execute some sql
            sqlstr = "CREATE TABLE hello (a int, b char);";
            sqlstr += "INSERT INTO hello VALUES (0, 'hello');"
            sqlstr += "INSERT INTO hello VALUES (1, 'world');"
            db.run(sqlstr); // Run the query without returning anything

            var data = db.export();
            var buffer = new Buffer(data);
            fs.writeFileSync(dbf, buffer);

            db.close();
        }
    });

    },
    toString: function() {
        return "videoDB: db (" + this.db_file + ")";
    }
}); 

module.exports  = videoDb;
