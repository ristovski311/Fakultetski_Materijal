  const image = document.querySelectorAll('.displayImage');

  image.forEach((img) => {
    img.addEventListener('click', () => {
    img.style.animation = "none";
    img.offsetHeight;
    img.style.animation = 'rotateFull 1s';
  })
  });