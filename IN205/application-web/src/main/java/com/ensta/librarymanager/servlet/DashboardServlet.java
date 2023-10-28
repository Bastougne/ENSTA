package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.EmpruntServiceImpl;
import com.ensta.librarymanager.services.implementation.LivreServiceImpl;
import com.ensta.librarymanager.services.implementation.MembreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/dashboard" )
public class DashboardServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private EmpruntServiceImpl empruntServiceImpl = EmpruntServiceImpl.getInstance();
    private LivreServiceImpl livreServiceImpl = LivreServiceImpl.getInstance();
    private MembreServiceImpl membreServiceImpl = MembreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            request.setAttribute( "countEmprunt", empruntServiceImpl.count() );
            request.setAttribute( "countLivre", livreServiceImpl.count() );
            request.setAttribute( "countMembre", membreServiceImpl.count() );
            request.setAttribute( "ListCurrentEmprunt", empruntServiceImpl.getListCurrent() );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/dashboard.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        doGet( request, response );
    }
}
