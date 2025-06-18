namespace restorani.Code;

public record SastojakSaKolicinom(int IdSastojka, int Kolicina);
public record JelaSaSastojcima(Jelo Jelo, List<SastojakSaKolicinom> Sastojci);