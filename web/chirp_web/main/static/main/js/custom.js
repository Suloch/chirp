
$(document).on('click', '#submit', function(){
  var data = $('#program-text').val()
  $.post('/main/run/',
  {
    'program': data,
  },
  function(data, status){
    $('#output').val(data.output)
  });
});
