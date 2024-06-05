dialog = {
  {
      speaker = "Person A",
      text = "Magst du kirschen?",
      duration = 2,
      options = {
          { text = "Jaaaaaaa sehr gerne :)", next = 1 },
          { text = "Naja... :/", next = 2 },
          { text = "Buah! EKELHAFT D:", next = 4 }
      }
  },
  {
      speaker = "Person B",
      text = "Cool ich auch willst du eine?",
      duration = 2,
      options = {
        { text = "Ja Danke :)", next = 5 },
        { text = "Nein Danke :)", next = 4 }
    }
  },
  {
      speaker = "Person B",
      text = "Probier doch mal! Meine FRISCH GEERNTETEN KIRSCHEN sind die besten!",
      duration = 2,
      options = {
        { text = "Ja Danke :)", next = 5 },
        { text = "Nein Danke :/", next = 4 }
    }
  },
  {
      speaker = "Person A",
      text = "Bis später!",
      duration = 2,
      next = nil
  },
  {
    speaker = "Person B",
    text = "HINFORT MIT DIR!!!",
    duration = 2,
    next = 3
  },
    {
        speaker = "Person B",
        text = "Du erhältst eine FRISCH ANGEBAUTE KIRSCHE!!!",
        duration = 2,
        next = nil
    }

}
