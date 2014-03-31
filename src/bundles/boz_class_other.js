function Circle(radius) {
    this.radius = radius;
}

Circle.prototype = {
    get circumference() {
        return 2*Math.PI*this.radius;
    },

    get area() {
        return Math.PI*this.radius*this.radius;
    }
}

c = new Circle(10);
console.log(c.area); // Should output 314.159
console.log(c.circumference); // Should output 62.832