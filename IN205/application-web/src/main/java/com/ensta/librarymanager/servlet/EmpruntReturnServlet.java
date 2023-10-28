package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.EmpruntServiceImpl;
import com.ensta.librarymanager.services.implementation.MembreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/emprunt_return" )
public class EmpruntReturnServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private MembreServiceImpl membreServiceImpl = MembreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            request.setAttribute( "ListCurrentEmprunt", EmpruntServiceImpl.getInstance().getListCurrent() );
            request.setAttribute( "ListMembreEmpruntPossible", membreServiceImpl.getListMembreEmpruntPossible() );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/emprunt_return.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            int idEmprunt = Integer.valueOf( request.getParameter( "id" ) );
            EmpruntServiceImpl.getInstance().returnBook( idEmprunt );
            response.sendRedirect( "/TP3Ensta/emprunt_list" );
        } catch ( ServiceException e ) {
            e.printStackTrace();
            doGet( request, response );
        }
    }
}
