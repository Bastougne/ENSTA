package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.modele.Livre;
import com.ensta.librarymanager.services.implementation.EmpruntServiceImpl;
import com.ensta.librarymanager.services.implementation.LivreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/livre_details" )
public class LivreDetailsServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private EmpruntServiceImpl empruntServiceImpl = EmpruntServiceImpl.getInstance();
    private LivreServiceImpl livreServiceImpl = LivreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            Livre livre = livreServiceImpl.getById( Integer.valueOf( request.getParameter( "id" ) ) );
            request.setAttribute( "livre", livre );
            request.setAttribute( "ListEmprunt", empruntServiceImpl.getListCurrentByLivre( livre.getPrimaryKey() ) );

        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/livre_details.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            Livre livre = livreServiceImpl.getById( Integer.valueOf( request.getParameter( "id" ) ) );
            livre.setTitre( request.getParameter( "titre" ) );
            livre.setAuteur( request.getParameter( "auteur" ) );
            livre.setIsbn( request.getParameter( "isbn" ) );
            LivreServiceImpl.getInstance().update( livre );
            response.sendRedirect( "/TP3Ensta/livre_list" );
        } catch ( ServiceException e ) {
            e.printStackTrace();
            doGet( request, response );
        }
    }
}
