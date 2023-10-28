package com.ensta.librarymanager.services.implementation;

import com.ensta.librarymanager.dao.implementation.LivreDaoImpl;
import com.ensta.librarymanager.exception.DaoException;
import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.modele.Livre;
import com.ensta.librarymanager.services.interfaces.LivreService;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class LivreServiceImpl implements LivreService {
    private static LivreServiceImpl instance;

    private LivreServiceImpl() {}

    public static LivreServiceImpl getInstance() {
        if ( instance == null )
            instance = new LivreServiceImpl();
        return instance;
    }

    public List<Livre> getList() throws ServiceException {
        List<Livre> list;
        try {
            list = LivreDaoImpl.getInstance().getList();
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return list;
    }

    public List<Livre> getListDispo() throws ServiceException {
        List<Livre> listLivre, list = new ArrayList<Livre>();
        try {
            listLivre = LivreDaoImpl.getInstance().getList();
            for ( Livre livre : listLivre ) {
                if ( EmpruntServiceImpl.getInstance().isLivreDispo( livre.getPrimaryKey() ) )
                    list.add( livre );
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

    public Livre getById( int id ) throws ServiceException {
        Livre livre;
        try {
            livre = LivreDaoImpl.getInstance().getById( id );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return livre;
    }

    public int create( String titre, String auteur, String isbn ) throws ServiceException {
        int created;
        try {
            if ( titre == "" )
                throw new ServiceException();
            created = LivreDaoImpl.getInstance().create( titre, auteur, isbn );
        } catch ( DaoException e ) {
            e.printStackTrace();
            throw new ServiceException();
        } catch ( SQLException e ) {
            e.printStackTrace();
            throw new ServiceException();
        }
        return created;
    }

    public void update( Livre livre ) throws ServiceException {
        try {
            if ( livre.getTitre() == "" )
                throw new ServiceException();
            LivreDaoImpl.getInstance().update( livre );
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
            LivreDaoImpl.getInstance().delete( id );
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
            count = LivreDaoImpl.getInstance().count();
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
