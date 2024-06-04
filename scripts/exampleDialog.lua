dialog = {
  {
      speaker = "Person A",
      text = "Hallo! Wie geht es dir?",
      duration = 2,
      options = {
          { text = "Gut, danke!", next = 1 },
          { text = "Nicht so gut.", next = 2 }
      }
  },
  {
      speaker = "Person B",
      text = "Das freut mich zu hören!",
      duration = 2,
      next = 3
  },
  {
      speaker = "Person B",
      text = "Oh, das tut mir leid.",
      duration = 2,
      next = 3
  },
  {
      speaker = "Person A",
      text = "Bis später!",
      duration = 2,
      next = nil
  }
}
