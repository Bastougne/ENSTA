package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.LivreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/livre_list" )
public class LivreListServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private LivreServiceImpl livreServiceImpl = LivreServiceImpl.getInstance();

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            request.setAttribute( "ListLivre", livreServiceImpl.getList() );
        } catch ( ServiceException e ) {
            e.printStackTrace();
        }

        getServletContext().getRequestDispatcher( "/WEB-INF/View/livre_list.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        doGet( request, response );
    }
}
