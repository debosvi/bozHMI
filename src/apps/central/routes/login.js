var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
    res.render('login', { title: 'Login', "username": req.session.username, "error": null  });
});

router.post('/', function(req, res) {
    req.session.username = req.body.username;
    res.redirect("/");
});

module.exports = router;
