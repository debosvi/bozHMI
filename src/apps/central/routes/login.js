var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
    res.render('login', { title: 'Login', "username": req.session.username, "error": null  });
});

router.post('/', function(req, res) {
    console.log("login post data: (" + JSON.stringify(req.body) + ")");
    if(req.body.login)
        req.session.login = req.body.login;
    else
        req.session.login = "";
    res.redirect('/');
});

module.exports = router;
