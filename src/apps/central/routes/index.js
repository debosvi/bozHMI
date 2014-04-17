var express = require('express');
var router = express.Router();

function requireLogin (req, res, next) {
    if (req.session.login && req.session.login !== "") {
        // User is authenticated, let him in
        next();
    } else {
        // Otherwise, we redirect him to login form
        res.redirect("/login");
    }
}

/* GET home page. */
router.get('/', [requireLogin], function(req, res, next) {
    const data = { title: "Express", login: req.session.login };
    res.render('index', data);
});

module.exports = router;
