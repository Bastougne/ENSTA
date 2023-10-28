package com.ensta.librarymanager.services.implementation;

import com.ensta.librarymanager.dao.implementation.EmpruntDaoImpl;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.modele.Emprunt;
import com.ensta.librarymanager.modele.Membre;
import com.ensta.librarymanager.services.interfaces.EmpruntService;
import java.sql.SQLException;
import java.time.LocalDate;
import java.util.List;

public class EmpruntServiceImpl implements EmpruntService {
    private static EmpruntServiceImpl instance;

    private EmpruntServiceImpl() {}

    public static EmpruntServiceImpl getInstance() {
        if ( instance == null )
            instance = new EmpruntServiceImpl();
        return instance;
    }

    public List<Emprunt> getList() throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().getList();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public List<Emprunt> getListCurrent() throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().getListCurrent();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public List<Emprunt> getListCurrentByMembre( int idMembre ) throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().getListCurrentByMembre( idMembre );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public List<Emprunt> getListCurrentByLivre( int idLivre ) throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().getListCurrentByLivre( idLivre );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public Emprunt getById( int id ) throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().getById( id );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public void create( int idMembre, int idLivre, LocalDate dateEmprunt ) throws ServiceException {
        try {
            EmpruntDaoImpl.getInstance().create( idMembre, idLivre, dateEmprunt );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public void returnBook( int id ) throws ServiceException {
        try {
            Emprunt emprunt = EmpruntDaoImpl.getInstance().getById( id );
            emprunt.setDateRetour( LocalDate.now() );
            EmpruntDaoImpl.getInstance().update( emprunt );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public int count() throws ServiceException {
        try {
            return EmpruntDaoImpl.getInstance().count();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public boolean isLivreDispo( int idLivre ) throws ServiceException {
        try {
            return ( EmpruntDaoImpl.getInstance().getListCurrentByLivre( idLivre ).size() == 0 );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public boolean isEmpruntPossible( Membre membre ) throws ServiceException {
        try {
            int nombreEmprunts = EmpruntDaoImpl.getInstance().getListCurrentByMembre( membre.getPrimaryKey() ).size();
            return ( nombreEmprunts < membre.getAbonnement().nombreMaxEmprunts );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }
}
