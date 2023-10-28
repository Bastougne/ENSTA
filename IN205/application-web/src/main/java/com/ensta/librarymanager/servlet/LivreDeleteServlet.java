package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.modele.Livre;
import com.ensta.librarymanager.services.implementation.LivreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/livre_delete" )
public class LivreDeleteServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    LivreServiceImpl livreServiceImpl = LivreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            Livre livre = livreServiceImpl.getById( Integer.valueOf( request.getParameter( "id" ) ) );
            request.setAttribute( "current", livre );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }
        
        getServletContext().getRequestDispatcher( "/WEB-INF/View/livre_delete.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            int idLivre = Integer.valueOf( request.getParameter( "id" ) );
            LivreServiceImpl.getInstance().delete( idLivre );
            response.sendRedirect( "/TP3Ensta/livre_list" );
        } catch ( ServiceException e ) {
            e.printStackTrace();
            doGet( request, response );
        }
    }
}
