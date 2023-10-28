package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.EmpruntServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/emprunt_list" )
public class EmpruntListServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private EmpruntServiceImpl empruntServiceImpl = EmpruntServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            request.setAttribute( "ListEmprunt", empruntServiceImpl.getList() );
            request.setAttribute( "ListCurrentEmprunt", empruntServiceImpl.getListCurrent() );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/emprunt_list.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        doGet( request, response );
    }
}
