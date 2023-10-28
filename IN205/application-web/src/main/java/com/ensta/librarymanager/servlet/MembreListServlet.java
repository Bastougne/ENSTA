package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.MembreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/membre_list" )
public class MembreListServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private MembreServiceImpl membreServiceImpl = MembreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            request.setAttribute( "ListMembre", membreServiceImpl.getList() );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/membre_list.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        doGet( request, response );
    }
}
