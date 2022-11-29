const mongoose = require('mongoose');
mongoose.connect('mongodb+srv://duro:014753@cluster0.syszl.mongodb.net/file_upload?retryWrites=true&w=majority', {
  useNewUrlParser: true,
  useUnifiedTopology: true,
  useCreateIndex: true
});