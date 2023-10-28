package com.ensta.librarymanager.servlet;

import com.ensta.librarymanager.exception.ServiceException;
import com.ensta.librarymanager.services.implementation.MembreServiceImpl;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet( "/membre_add" )
public class MembreAddServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        getServletContext().getRequestDispatcher( "/WEB-INF/View/membre_add.jsp" ).forward( request, response );
    }

    protected void doPost( HttpServletRequest request, HttpServletResponse response ) throws ServletException, IOException {
        try {
            String nom = request.getParameter( "nom" );
            String prenom = request.getParameter( "prenom" );
            String adresse = request.getParameter( "adresse" );
            String email = request.getParameter( "email" );
            String telephone = request.getParameter( "telephone" );
            MembreServiceImpl.getInstance().create( nom, prenom, adresse, email, telephone );
            response.sendRedirect( "/TP3Ensta/membre_list" );
        } catch ( ServiceException e ) {
            e.printStackTrace();
            doGet( request, response );
        }
    }
}
