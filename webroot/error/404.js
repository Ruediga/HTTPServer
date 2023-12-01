// type text at target with desired delay
function teletypeText(targetId, text, speed) {
  const targetElement = document.getElementById(targetId);
  let n = 0;

  const typeTimer = setInterval(() => {
    n++;
    // each iteration show more of the text
    targetElement.innerHTML = text.slice(0, n);
    if (n === text.length) {
      clearInterval(typeTimer);
      showBlinkingCursor(targetElement, text);
    }
  }, speed);
}

// animate cursor at the end of text
function showBlinkingCursor(targetElement, text) {
  let swap = 0;
  setInterval(() => {
    if (swap === 0) {
      targetElement.innerHTML = text + "|";
      swap = 1;
    } else {
      targetElement.innerHTML = text;
      swap = 0;
    }
  }, 500);
}

teletypeText('notfound', '404, Not Found', 100);