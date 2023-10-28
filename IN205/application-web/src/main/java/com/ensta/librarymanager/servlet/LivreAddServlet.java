package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.LivreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/livre_add" )
public class LivreAddServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    LivreServiceImpl livreServiceImpl = LivreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        getServletContext().getRequestDispatcher( "/WEB-INF/View/livre_add.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            String titre = request.getParameter( "titre" );
            String auteur = request.getParameter( "auteur" );
            String isbn = request.getParameter( "isbn" );
            LivreServiceImpl.getInstance().create( titre, auteur, isbn );
            response.sendRedirect( "/TP3Ensta/livre_list" );
        } catch ( ServiceException e ) {
            e.printStackTrace();
            doGet( request, response );
        }
    }
}
