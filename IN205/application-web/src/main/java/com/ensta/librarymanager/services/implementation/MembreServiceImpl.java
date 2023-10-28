package com.ensta.librarymanager.services.implementation;

import com.ensta.librarymanager.dao.implementation.MembreDaoImpl;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.modele.Membre;
import com.ensta.librarymanager.services.interfaces.MembreService;
import com.ensta.librarymanager.utils.Abonnement;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class MembreServiceImpl implements MembreService {
    private static MembreServiceImpl instance;

    private MembreServiceImpl() {}

    public static MembreServiceImpl getInstance() {
        if ( instance == null )
            instance = new MembreServiceImpl();
        return instance;
    }

    public List<Membre> getList() throws ServiceException {
        List<Membre> list;
        try {
            list = MembreDaoImpl.getInstance().getList();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return list;
    }

    public List<Membre> getListMembreEmpruntPossible() throws ServiceException {
        List<Membre> listMembres, list = new ArrayList<Membre>();
        try {
            listMembres = MembreDaoImpl.getInstance().getList();
            for ( Membre membre : listMembres ) {
                if ( EmpruntServiceImpl.getInstance().isEmpruntPossible( membre ) )
                    list.add( membre );
            }
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return list;
    }

    public Membre getById( int id ) throws ServiceException {
        Membre membre;
        try {
            membre = MembreDaoImpl.getInstance().getById( id );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return membre;
    }

    public int create( String nom, String prenom, String adresse, String email, String telephone ) throws ServiceException {
        int created;
        try {
            if ( nom == "" || prenom == "" )
                throw new ServiceException();
            created = MembreDaoImpl.getInstance().create( nom.toUpperCase(), prenom, adresse, email, telephone, Abonnement.BASIC );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return created;
    }

    public void update( Membre membre ) throws ServiceException {
        try {
            if ( membre.getNom() == "" || membre.getPrenom() == "" )
                throw new ServiceException();
            membre.setNom( membre.getNom().toUpperCase() );
            MembreDaoImpl.getInstance().update( membre );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public void delete(int id)throws ServiceException {
        try {
            MembreDaoImpl.getInstance().delete( id );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
    }

    public int count() throws ServiceException {
        int count;
        try {
            count = MembreDaoImpl.getInstance().count();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return count;
    }
}
