const { useRef, useEffect } = React;

function App()
{
    const contentRef = useRef(null);

    useEffect(() => {
    let degrees = 0;
    const intervalId = setInterval(() => {
      if (contentRef.current) {
        contentRef.current.style.border = "0.2rem solid transparent";
        contentRef.current.style.borderImage = `linear-gradient(${degrees}deg, var(--primary-decoration-color), var(--secondary-decoration-color))`;
        contentRef.current.style.borderImageSlice = "1";
        contentRef.current.style.borderRadius = "20px";
        degrees = (degrees + 1) % 360;
      }
    }, 100);

        return () => clearInterval(intervalId);
    }, []);

    return (
    <div className="root-container">
      <header className="main-header">
        <h1>Imenik</h1>
      </header>

      <div className="content-container" ref={contentRef}>
        {/* App content will go here */}
      </div>

      <footer className="main-footer">
        <p>&copy; Ristovski Nikola, 2025</p>
        <p>Elektronski fakultet, Niš</p>
      </footer>
    </div>
  );
}



const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);


