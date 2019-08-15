
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

$(document).on('click', '#submit-Modulus', function(){
  var data = `
  (program to find modulus using user defined function)
    (Author : Suloch)

    Midnight takes your heart and your soul
    While your heart is as high as your soul
    Put your heart without your soul into your heart

    Give back your heart

    Darkness was alone
    Silence was haunting
    Whisper Midnight taking Silence, Darkness
`;
  $('#program-text').val(data);
  $.post('/main/run/',
  {
    'program': data,
  },
  function(data, status){
    $('#output').val(data.output)
  });
});
$(document).on('click', '#submit-Factorial', function(){
  var data = `
  (Program to calclate factorial for a number recrusively)
  (Author : Suloch)


  Everyone takes the bait
  If the bait is nothing
  Put nobody into the chaos
  Build the chaos up
  Else
  Put the bait of Everyone taking the bait without 1 into the chaos

  Give back the chaos

  Say Everyone taking 6
  `;
  $('#program-text').val(data);
  $.post('/main/run/',
  {
    'program': data,
  },
  function(data, status){
    $('#output').val(data.output)
  });
});
$(document).on('click', '#submit-Fibonacci', function(){
  var data = `
  (Program to print first 14 fibonacci numbers)
  (Author : Suloch)

  Put nothing into my words
  my promises were lies
  my truth was too
  Put my promises without my truth into my life
  Put my life into my promises
  the thought was a sign
  Whisper my promises
  While the thought is higher than nothing
  Whisper my promises
  Put my life into my words
  Put my promises into my life
  Put my life with my words into my promises
  Knock the thought down

  (End of Program)
`;
  $('#program-text').val(data);
  $.post('/main/run/',
  {
    'program': data,
  },
  function(data, status){
    $('#output').val(data.output)
  });
});
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
