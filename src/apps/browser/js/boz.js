// An example Backbone application contributed by
// [Jérôme Gravel-Niquet](http://jgn.me/). This demo uses a simple
// [LocalStorage adapter](backbone-localstorage.html)
// to persist Backbone models within your browser.

// Load the application once the DOM is ready, using `jQuery.ready`:
$(document).ready(function() {

  // Todo Model
  // ----------

  // Our basic **Todo** model has `title`, `order`, and `done` attributes.
  var BozModel = Backbone.Model.extend({

    // Default attributes for the todo item.
    defaults: function() {
      return {
        title: "boz app...",
        activated: false
      };
    },

    // Toggle the `done` state of this todo item.
    toggle: function() {
      this.save({activated: !this.get("activated")});
    }

  });

  var bm = new BozModel();
  // Todo Item View
  // --------------

  // The DOM element for a todo item...
  var BozView = Backbone.View.extend({

    //... is a list tag.
    tagName:  "div",

    // Cache the template function for a single item.
    template: _.template($('#boz-template').html()),

    // The DOM events specific to an item.
    events: {
      "click .boz-item"   : "toggleDone"
    },

    // The TodoView listens for changes to its model, re-rendering. Since there's
    // a one-to-one correspondence between a **Todo** and a **TodoView** in this
    // app, we set a direct reference on the model for convenience.
    initialize: function() {
      this.listenTo(this.model, 'change', this.render);
      this.listenTo(this.model, 'destroy', this.remove);
    },

    // Re-render the titles of the todo item.
    render: function() {
      this.$el.html(this.template(this.model.toJSON()));
      this.$el.toggleClass('activated', this.model.get('activated'));
  //    this.input = this.$('.edit');
      return this;
    },

    // Toggle the `"done"` state of the model.
    toggleDone: function() {
      this.model.toggle();
    },

    // Remove the item, destroy the model.
    clear: function() {
      this.model.destroy();
    }

  });

  // The Application
  // ---------------

  // Our overall **AppView** is the top-level piece of UI.
  var AppView = Backbone.View.extend({

    // Instead of generating a new element, bind to the existing skeleton of
    // the App already present in the HTML.
    el: $("#container"),

    // Our template for the line of statistics at the bottom of the app.
    statsTemplate: _.template($('#boz-template').html()),

    // Delegated events for creating new items, and clearing completed ones.
    events: {
    },

    // At initialization we bind to the relevant events on the `Todos`
    // collection, when items are added or changed. Kick things off by
    // loading any preexisting todos that might be saved in *localStorage*.
    initialize: function() {
        console.log("AppView initialize");

        var bm = new BozModel;
      this.elem = new BozView({model: bm});
      this.$el.append(this.elem.render().el);
    },

    // Re-rendering the App just means refreshing the statistics -- the rest
    // of the app doesn't change.
    render: function() {
        console.log("AppView render");
    }

  });

var view = new AppView;
}); 
