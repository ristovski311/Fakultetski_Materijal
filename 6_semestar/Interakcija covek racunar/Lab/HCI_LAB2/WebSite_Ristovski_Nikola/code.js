
//
// PRIKAZ KONTAKTA
//

function Kontakt(props) {
  return <div className="contact-card">
    <h1> {props.podaci.ime + " " + props.podaci.prezime} </h1>
    <h2> {props.podaci.broj} </h2>
    <h3> {props.podaci.email} </h3>
    <button type="button" onClick={props.onEdit} className="btn-change">
      Izmeni
    </button>
  </div>
}


//
// PRIKAZ EDITOVANJA
//


function KontaktEdit(props) {
  return <div className="contact-edit-card">
    <form onSubmit={props.onSubmit} className="contact-edit-form">
      <input className="edit-input edit-ime" type="text" name="ime" value={props.podaci.ime} onChange={props.onChange} placeholder="ime..."></input>
      <input className="edit-input edit-prezime" type="text" name="prezime" value={props.podaci.prezime} onChange={props.onChange} placeholder="prezime..."></input>
      <input className="edit-input edit-broj" type="text" name="broj" value={props.podaci.broj} onChange={props.onChange} placeholder="broj..."></input>
      <input className="edit-input edit-email" type="email" name="email" value={props.podaci.email} onChange={props.onChange} placeholder="email..."></input>
      <div className="edit-btns">
        <button type="submit" className="btn-edit-submit">
          Potvrdi
        </button>
        <button type="button" onClick={props.onCancel} className="btn-edit-cancel">
          Odustani
        </button>
      </div>
    </form >
  </div >
}


//
//DODAJ KONTAKT COMPONENT
//

function DodajKontakt(props) {
  return <div className="add-contact-container">
    <form onSubmit={props.onSubmit} className="add-contact-form">
      <input
        className="add-input"
        type="text"
        name="ime"
        value={props.noviKontakt.ime || ""}
        onChange={props.onChange}
      />
      <label className="add-label">
        Ime
      </label>
      <input
        className="add-input"
        type="text"
        name="prezime"
        value={props.noviKontakt.prezime || ""}
        onChange={props.onChange}
      />

      <label className="add-label">
        Prezime
      </label>
      <input
        className="add-input"
        type="email"
        name="email"
        value={props.noviKontakt.email || ""}
        onChange={props.onChange}
      />

      <label className="add-label">
        Email
      </label>
      <input
        className="add-input"
        type="text"
        name="broj"
        value={props.noviKontakt.broj || ""}
        onChange={props.onChange}
      />
      <label className="add-label">
        Broj
      </label>
      <button type="submit" className="btn-add">
        DODAJ
      </button>
    </form>
  </div>
}



//
//APP
//


function App() {

  //
  //KONTAKTI
  const [kontakti, setKontakti] = React.useState([]);

  //
  //DODAVANJE NOVOG KONTAKTA

  const [showForm, setShowForm] = React.useState(false);

  const [noviKontakt, setNoviKontakt] = React.useState(
    {
      ime: "",
      prezime: "",
      email: "",
      broj: ""
    }
  );

  const handleChangeAddInput = (event) => {
    const { name, value } = event.target;
    setNoviKontakt(prev => ({ ...prev, [name]: value }));
  }

  const handleSubmitNewKontakt = (event) => {
    event.preventDefault();

    if (!noviKontakt.ime || !noviKontakt.prezime || !noviKontakt.email || !noviKontakt.broj) {
      alert("Morate popuniti sva polja za unos novog kontakta!");
      return;
    }

    const novi = {
      ...noviKontakt,
      id: noviKontakt.broj
    };

    setKontakti(prev => [...prev, novi]);
    setNoviKontakt({
      ime: "",
      prezime: "",
      email: "",
      broj: ""
    });

    setShowForm(false);

  }

  //
  //FILTRIRANJE

  const [filter, setFilter] = React.useState("");

  const filtriraniKontakti = kontakti.filter((k) => {
    const tekst = filter.toLowerCase();
    return (
      k.ime.toLowerCase().includes(tekst) ||
      k.prezime.toLowerCase().includes(tekst) ||
      k.email.toLowerCase().includes(tekst) ||
      k.broj.toLowerCase().includes(tekst)
    );
  })

  //
  //EDITOVANJE

  const [selectedID, setSelectedID] = React.useState(null);

  const [editKontakt, setEditKontakt] = React.useState({
    ime: "",
    prezime: "",
    email: "",
    broj: ""
  });

  const handleEdit = (kontakt) => {
    setSelectedID(kontakt.id);
    setEditKontakt({ ...kontakt });
  };

  const handleCancel = () => {
    setSelectedID(null);
  }

  const handleEditChange = (event) => {
    const { name, value } = event.target;
    setEditKontakt(prev => ({ ...prev, [name]: value }));
  };

  const handleUpdateSubmit = (event, id) => {
    event.preventDefault();

    if (!editKontakt.ime || !editKontakt.prezime || !editKontakt.email || !editKontakt.broj) {
      alert("Sva polja moraju biti popunjena!");
      return;
    }

    const azurirano = kontakti.map((k) =>
      k.id === id ? { ...editKontakt, id } : k
    );

    setKontakti(azurirano);
    setSelectedID(null);
  };

  //
  // APP RETURN

  return <>
    <div className="content-container">

      {/* HEADER */}

      <header className="main-header">
        <h1>Imenik</h1>
      </header>

      {/* DODAVANJE KONTAKTA */}

      <div className="add-contact">
        <h2>Dodaj novi kontakt:</h2>
        <button className="add-toggle" onClick={() => setShowForm(prev => !prev)}>
          {showForm ? "–" : "+"}
        </button>
        {showForm && (
          <DodajKontakt
            noviKontakt={noviKontakt}
            onSubmit={handleSubmitNewKontakt}
            onChange={handleChangeAddInput}
          />
        )}
      </div>

      {/* PRIKAZ LISTE KONTAKATA */}

      <div className="contact-list-container">
        <h2 className="contact-list-heading">Moji kontakti</h2>

        {/* FILTRIRANJE */}

        <form className="filter-form">
          <label className="filter-label">
            Filtriraj
          </label>
          <input className="filter-input" type="text" value={filter} onChange={(e) => setFilter(e.target.value)} placeholder="Unesite filter (ime, prezime, broj, email)"></input>
        </form>

        {/* LISTA KONTAKATA */}

        <div className="contact-list">
          {filtriraniKontakti.map((kontakt) =>
            kontakt.id === selectedID ? (
              <KontaktEdit
                key={kontakt.id}
                podaci={editKontakt}
                onChange={handleEditChange}
                onCancel={handleCancel}
                onSubmit={(e) => handleUpdateSubmit(e, kontakt.id)}>
              </KontaktEdit>
            ) : (
              <Kontakt key={kontakt.broj} podaci={kontakt} onEdit={() => handleEdit(kontakt)}></Kontakt>
            )
          )}
        </div>
      </div>
    </div>
    <footer className="main-footer">
      <p>Ristovski Nikola</p>
      <p>Elektronski fakultet, Nis</p>
      <p>2025</p>
    </footer>
  </>
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);


