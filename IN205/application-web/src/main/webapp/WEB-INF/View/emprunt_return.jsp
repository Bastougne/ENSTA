<%@ taglib uri = "http://java.sun.com/jsp/jstl/core" prefix = "c" %>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Library Management</title>
  <meta content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no' name='viewport'>
  <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css" rel="stylesheet" type="text/css" />
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/0.98.0/css/materialize.min.css">
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
  <link href="assets/css/custom.css" rel="stylesheet" type="text/css" />
</head>

<body>
  <jsp:include page='menu.jsp'></jsp:include>
  <main>
    <section class="content">
      <div class="page-announce valign-wrapper">
        <a href="#" data-activates="slide-out" class="button-collapse valign hide-on-large-only"><i class="material-icons">menu</i></a>
        <h1 class="page-announce-text valign">Retour d'un livre</h1>
      </div>
      <div class="row">
      <div class="container">
        <h5>Selectionner le livre a retourner</h5>
        <div class="row">
	      <form action="/TP3Ensta/emprunt_return" method="post" class="col s12">
	        <div class="row">
	          <div class="input-field col s12">
	            <select id="id" name="id" class="browser-default">
                <c:choose>
                  <c:when test="${not empty param.id}">
	                  <option value="" disabled>---</option>
                  </c:when>
                  <c:otherwise>
                    <option value="" disabled selected>---</option>
                  </c:otherwise>
                </c:choose>
                <c:forEach var="current" items="${ListCurrentEmprunt}">
                  <c:choose>
                    <c:when test="${param.id==current.primaryKey}">
	                    <option selected value="${current.primaryKey}">"${current.livre.titre}", emprunte par ${current.membre.prenom} ${current.membre.nom}</option>
                    </c:when>
                    <c:otherwise>
                      <option value="${current.primaryKey}">"${current.livre.titre}", emprunte par ${current.membre.prenom} ${current.membre.nom}</option>
                    </c:otherwise>
                  </c:choose>
                </c:forEach>
                </select>
	          </div>
	        </div>
	        <div class="row center">
	          <button class="btn waves-effect waves-light" type="submit">Retourner le livre</button>
	          <button class="btn waves-effect waves-light orange" type="reset">Annuler</button>
	        </div>
	      </form>
	    </div>
      </div>
      </div>
    </section>
  </main>
  <jsp:include page='footer.jsp'></jsp:include>
  <script>
    document.addEventListener('DOMContentLoaded', function() {
	  var elems = document.querySelectorAll('select');
	  var instances = M.FormSelect.init(elems, {});
	});
  </script>
</body>
</html>
